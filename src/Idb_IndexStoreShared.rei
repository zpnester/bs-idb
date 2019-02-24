type t;

/* get: query (not key) is required */
let get: (t, Idb_Query.t) => Js.Promise.t(Js.Json.t);
/* getAll: query (not key) is optional */
let getAll:
  (t, ~query: Idb_Query.t=?, ~count: int=?, unit) =>
  Js.Promise.t(array(Js.Json.t));
let getAllKeys:
  (t, ~query: Idb_Query.t=?, ~count: int=?, unit) =>
  Js.Promise.t(array(Js.Json.t));
let count: (t, ~query: Idb_Query.t=?, unit) => Js.Promise.t(int);
let openCursor:
  (t, ~query: Idb_Query.t=?, ~direction: [`next | `nextunique | `prev | `prevunique ]=?, unit) =>
  Js.Promise.t(option(Idb_Cursor.t));
let openKeyCursor:
  (t, ~query: Idb_Query.t=?, ~direction: [`next | `nextunique | `prev | `prevunique ]=?, unit) =>
  Js.Promise.t(option(Idb_Cursor.t));

/* "Due to the microtask issues in some browsers, iterating over a cursor using promises doesn't always work" */

let iterateCursor: (t, option(Idb_IDBCursor.t) => unit) => unit;
let iterateKeyCursor: (t, option(Idb_IDBCursor.t) => unit) => unit;