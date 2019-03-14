include (module type of Idb_IndexStoreShared);

[@bs.get] external name: t => string = "name";
[@bs.get] external keyPath: t => Js.Json.t = "keyPath";
[@bs.get] external multiEntry: t => bool = "multiEntry";
[@bs.get] external unique: t => bool = "unique";

let getKey: (t, ~query: Idb_Query.t=?, unit) => Js.Promise.t(Js.Json.t);
