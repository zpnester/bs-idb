module IDBRequest = Idb_IDBRequest;
module DOMStringList = Idb_DOMStringList;
module Query = Idb_Query;
module IDBCursorDirection = Idb_IDBCursorDirection;
module Cursor = Idb_Cursor;
module IDBCursor = Idb_IDBCursor;
module IndexStoreShared = Idb_IndexStoreShared;
module Index = Idb_Index;
module ObjectStore = Idb_ObjectStore;
module Transaction = Idb_Transaction;
module DB = Idb_DB;
module UpgradeDB = Idb_UpgradeDB;

type t;
let indexedDbSupported: unit => bool;
let idb: t;
let open_:
  (t, string, int, Idb_UpgradeDB.t => unit) => Js.Promise.t(Idb_DB.t);
let delete: (t, string) => Js.Promise.t(unit);