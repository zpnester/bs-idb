include (module type of Idb_IndexStoreShared);

[@bs.get] external name: t => string = "name";
[@bs.get] external keyPath: t => Js.Json.t = "keyPath";
let indexNames: t => array(string);
[@bs.get] external autoIncrement: t => bool = "autoIncrement";

let put: (t, ~value: 'value, ~key: 'key=?, unit) => Js.Promise.t(unit);
let add: (t, ~value: 'value, ~key: 'key=?, unit) => Js.Promise.t(unit);
[@bs.send] external delete: (t, 'key) => Js.Promise.t(unit) = "delete";
[@bs.send] external clear: t => Js.Promise.t(unit) = "clear";
[@bs.send] external deleteIndex: (t, string) => unit = "deleteIndex";
let createIndex:
  (
    t,
    string,
    ~keyPath: [ | `String(string) | `Strings(array(string))]=?,
    ~unique: bool=?,
    ~multiEntry: bool=?,
    unit
  ) =>
  Idb_Index.t;
let index: (t, string) => Idb_Index.t;