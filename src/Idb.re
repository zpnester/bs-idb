module IDBRequest = Idb_IDBRequest;
module IDBCursor = Idb_IDBCursor;
module Query = Idb_Query;
module IDBCursorDirection = Idb_IDBCursorDirection;
module Cursor = Idb_Cursor;
module Index = Idb_Index;
module ObjectStore = Idb_ObjectStore;
module Transaction = Idb_Transaction;
module DB = Idb_DB;
module UpgradeDB = Idb_UpgradeDB;

type t;

[@bs.send]
external open_:
  (t, string, int, Idb_UpgradeDB.t => unit) => Js.Promise.t(Idb_DB.t) =
  "open";

[@bs.send] external delete: (t, string) => Js.Promise.t(unit) = "delete";

[@bs.module] external idb_: t = "idb";

let idb__: Js.Nullable.t(t) = [%raw {|
(typeof indexedDB == "object") ? (require("idb")) : (null)
|}];

let idb = idb__->Js.Nullable.toOption;