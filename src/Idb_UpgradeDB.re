include Idb_DBBase;

type key_path = [ | `String(string) | `Strings(array(string))];

/* this is a property rather than a method. It's a Transaction representing the upgrade transaction */
[@bs.get] external transaction: t => Idb_Transaction.t = "transaction";
[@bs.get] external oldVersion: t => int = "oldVersion";

[@bs.send]
external createObjectStore_:
  (t, string, {. "autoIncrement": Js.Nullable.t(bool)}) => Idb_ObjectStore.t =
  "createObjectStore";

let createObjectStore =
    (
      self: t,
      name: string,
      ~keyPath: option(key_path)=?,
      ~autoIncrement: option(bool)=?,
      (),
    ) => {
  let opts = {"autoIncrement": Js.Nullable.fromOption(autoIncrement)};
  let opts =
    switch (keyPath) {
    | Some(`String(str)) => Js.Obj.assign(opts, {"keyPath": str})
    | Some(`Strings(strs)) => Js.Obj.assign(opts, {"keyPath": strs})
    | None => opts
    };
  self->createObjectStore_(name, opts);
};

[@bs.send]
external deleteObjectStore: (t, string) => unit = "deleteObjectStore"; /* deleteObjectStore, not delete */
