type t;
type idb_cursor_source;

let source: t => idb_cursor_source;

let direction: t => [ | `next | `nextunique | `prev | `prevunique];

[@bs.get] external value: t => Js.Json.t = "value";

[@bs.send] external advance: (t, int) => unit = "advance";

[@bs.send] external delete: t => Idb_IDBRequest.t = "delete";

[@bs.send] external update: (t, 'value) => Idb_IDBRequest.t = "update";

[@bs.get] external key: t => Js.Json.t = "key";

let continue: (t, ~key: 'key=?, unit) => unit;

[@bs.send]
external continuePrimaryKey: (t, 'key, 'pkey) => unit = "continuePrimaryKey";
