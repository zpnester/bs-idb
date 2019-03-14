module IDBRequest = Idb_IDBRequest;
module IDBCursor = Idb_IDBCursor;
module Query = Idb_Query;
module Cursor = Idb_Cursor;
module Index = Idb_Index;
module ObjectStore = Idb_ObjectStore;
module Transaction = Idb_Transaction;
module DB = Idb_DB;
module UpgradeDB = Idb_UpgradeDB;

type t;

[@bs.send]
external openDb:
  (t, string, int, Idb_UpgradeDB.t => unit) => Js.Promise.t(Idb_DB.t) =
  "openDb";

[@bs.send] external deleteDb: (t, string) => Js.Promise.t(unit) = "deleteDb";

let idb__: Js.Nullable.t(t) = [%raw
  {|
(typeof indexedDB == "object") ? (require("idb")) : (null)
|}
];

let idb = idb__->Js.Nullable.toOption;
