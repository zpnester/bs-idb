include Idb_DBBase;

[@bs.send]
external transaction: (t, string, string) => Idb_Transaction.t = "transaction";

[@bs.send]
external transactionMany: (t, array(string), string) => Idb_Transaction.t =
  "transaction";

let transactionReadOnly: (t, string) => Idb_Transaction.t =
  (db, store) => transaction(db, store, "readonly");

let transactionManyReadOnly: (t, array(string)) => Idb_Transaction.t =
  (db, storeNames) => transactionMany(db, storeNames, "readonly");

let transactionReadWrite: (t, string) => Idb_Transaction.t =
  (db, store) => transaction(db, store, "readwrite");

let transactionManyReadWrite: (t, array(string)) => Idb_Transaction.t =
  (db, storeNames) => transactionMany(db, storeNames, "readwrite");
/* readwriteflush is non-standard, Firefox-only */