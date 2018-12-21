module IDBRequest = Idb_IDBRequest;
module Query = Idb_Query;
module IDBCursorDirection = Idb_IDBCursorDirection;
module Cursor = Idb_Cursor;
module IDBCursor = Idb_IDBCursor;
module Index = Idb_Index;
module ObjectStore = Idb_ObjectStore;
module Transaction = Idb_Transaction;
module DB = Idb_DB;
module UpgradeDB = Idb_UpgradeDB;

type t;
let idb: option(t);
let open_:
  (t, string, int, Idb_UpgradeDB.t => unit) => Js.Promise.t(Idb_DB.t);
let delete: (t, string) => Js.Promise.t(unit);