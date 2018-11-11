include (module type of Idb_DBBase);

/* let transaction: (t, string, string) => Transaction.t;
   let transactionMany: (t, array(string), string) => Transaction.t; */

let transactionReadOnly: (t, string) => Idb_Transaction.t;
let transactionManyReadOnly: (t, array(string)) => Idb_Transaction.t;

let transactionReadWrite: (t, string) => Idb_Transaction.t;
let transactionManyReadWrite: (t, array(string)) => Idb_Transaction.t;