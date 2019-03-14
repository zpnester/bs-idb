include (module type of Idb_DBBase);

[@bs.get] external transaction: t => Idb_Transaction.t = "transaction";

[@bs.get] external oldVersion: t => int = "oldVersion";

let createObjectStore:
  (
    t,
    string,
    ~keyPath: [ | `String(string) | `Strings(array(string))]=?,
    ~autoIncrement: bool=?,
    unit
  ) =>
  Idb_ObjectStore.t;

[@bs.send]
external deleteObjectStore: (t, string) => unit = "deleteObjectStore";
