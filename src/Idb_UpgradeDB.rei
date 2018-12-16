include (module type of Idb_DBBase);

/* "this is a property rather than a method. It's a Transaction representing the upgrade transaction" */
let transaction: t => Idb_Transaction.t;
let oldVersion: t => int;

let createObjectStore:
  (
    t,
    string,
    ~keyPath: [ | `String(string) | `Strings(array(string))]=?,
    ~autoIncrement: bool=?,
    unit
  ) =>
  Idb_ObjectStore.t;

let deleteObjectStore: (t, string) => unit;