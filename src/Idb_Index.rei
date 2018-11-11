include (module type of Idb_IndexStoreShared);

let name: t => string;
let keyPath: t => Idb_Types.any;
let multiEntry: t => bool;
let unique: t => bool;

let getKey:
  (t, ~query: Idb_Query.t=?, unit) => Js.Promise.t(option(Idb_Types.any));