# ElefantBlasterServerInterface

Desktop admin tool (wxWidgets GUI, desktop only) that connects to ElefantBlasterServer's admin endpoint (`wss://` 127.0.0.1:9003 by default, protobuf messages from ElefantBlasterCommon). Current features: login, server shutdown/restart, game-server control menu, User Management tab (Users / Groups / Roles / Permissions lists). Mentor mode: see workspace `CLAUDE.md`.

codebase-memory project: `K-git-ElefantBlaster-ElefantBlasterServerInterface`.

## Architecture

```text
wxIMPLEMENT_APP(ProcessControl)          ProcessControl : wxApp  (UI thread, the "controller")
  OnInit: LoggerManager, SettingsManager, ThreadPool, LoginFrame, AdminClient.Start()+Connect()

UI widgets ──wxQueueEvent(EVT_UI_*)──► ProcessControl ──► AdminClient::Request*/Send()
AdminClient (websocketpp TLS client, run loop on ThreadPool thread)
   OnMessage → parse protocol::ServerMessage → switch body_case()
   ──wxQueueEvent(EVT_NET_*, payload)──► ProcessControl   (connect/login/logout events)
                                     └─► TabUsers/TabGroups/TabRoles/TabPermissions::Instance()  (list results)
```

- **Threading rule**: the network thread never touches widgets. It packs data into a `wxThreadEvent` (`SetPayload<T>()`) and `wxQueueEvent`s it; the handler on the UI thread reads `GetPayload<T>()`.
- All custom events and their payload structs (`LoginSubmitParams`, `LoginResponseData`, `FilterUsersParams`) are declared in `src/common/events.hpp` and defined in `events.cpp`. Naming: `EVT_UI_*` = UI → controller, `EVT_NET_*` = network → UI.
- Login flow: `LoginFrame` → `EVT_UI_LOGIN_SUBMIT` → `AdminClient::LoginRequest` → `EVT_NET_LOGIN_APPROVED/REJECTED` → `ProcessControl` closes `LoginFrame`, creates `MainFrame`.
- Reconnect: on disconnect/error `AdminClient` emits `EVT_NET_RECONNECT`; `ProcessControl::OnNetReconnect` retries every 1s (delayed ThreadPool task) while on the login screen, or asks the user Reconnect/Logout when the main window is open.
- Session state is the singleton `Profile` (`#define AuthUser Profile::Instance()`): display name, permission set, cached lists. Tabs request data lazily on `EVT_UI_TAB_CHANGED` only if the cached list is empty.

## Source map (`src/`)

| Dir | Contents |
|-----|----------|
| `entrypoint/` | `wxIMPLEMENT_APP` |
| `control/` | `ProcessControl` (wxApp): event bindings, frame lifecycle |
| `network/` | `AdminClient` |
| `ui/` | `LoginFrame`, `MainFrame` (menus + status bar), `TabUserManage` (wxNotebook) → `user_manage/Tab{Users,Groups,Roles,Permissions}` (wxGrid), `ui_definitions.hpp` (`TabIndex`) |
| `entities/` | `Profile` |
| `common/` | `events`, `SettingsManager` (near-copy of the server's) |

UI mockups for planned screens (dashboard, logs, settings, users): `docs/designs/*.screen.md`.

## Adding a feature end-to-end

proto in Common → server handler (`AdminServer`) → `AdminClient::Request<X>()` + `OnMessage` case + `On<X>Respond` overloads → `wxDECLARE/DEFINE_EVENT(EVT_NET_<X>_SUCCESS/FAILURE)` → `Bind` in the receiving widget → UI trigger via `EVT_UI_*` handled in `ProcessControl`.

Config: `assets/configs/default/{app,client,logging}.json` (`/admin_server/host`, `/admin_server/port`).
