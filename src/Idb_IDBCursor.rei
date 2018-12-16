type t;
type idb_cursor_source;

let source: t => idb_cursor_source;
let direction: t => Idb_IDBCursorDirection.t;
let value: t => Js.Json.t;
let advance: (t, int) => unit;
let delete: t => Idb_IDBRequest.t;
let update: (t, 'value) => Idb_IDBRequest.t;
let key: t => Js.Json.t;
/* continue: key (not query) optional */
let continue: (t, ~key: 'key=?, unit) => unit;
/* continuePrimaryKey: keys (not queries) required */
let continuePrimaryKey: (t, 'key, 'pkey) => unit;