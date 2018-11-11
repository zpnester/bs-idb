type t;

let direction: t => Idb_IDBCursorDirection.t;
let value: t => Idb_Types.any;
let update: (t, 'value) => Js.Promise.t(unit);
let delete: t => Js.Promise.t(unit);

let key: t => option(Idb_Types.any);
let primaryKey: t => option(Idb_Types.any);
let advance: (t, int) => Js.Promise.t(option(t));
let continue: (t, ~key: 'key=?, unit) => Js.Promise.t(option(t));
let continuePrimaryKey: (t, 'key, 'pkey) => Js.Promise.t(option(t));