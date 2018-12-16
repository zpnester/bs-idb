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

/* this one won't work in service worker */
/* {| new Boolean('indexedDB' in window) |} */


/* naming empty parameter is important, 'function()' will not work in BuckleScript >= 4.0.7 */
let indexedDbSupported: unit => bool = [%bs.raw
  {|
    function(unit) {
        return typeof indexedDB === "object" ;
    }
  |}
];

type t;

[@bs.send]
external open_:
  (t, string, int, Idb_UpgradeDB.t => unit) => Js.Promise.t(Idb_DB.t) =
  "open";

[@bs.send] external delete: (t, string) => Js.Promise.t(unit) = "delete";

[@bs.module] external idb: t = "idb";