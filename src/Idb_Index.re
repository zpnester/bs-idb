include Idb_IndexStoreShared;

[@bs.get] external name: t => string = "";
[@bs.get] external keyPath: t => Js.Json.t = "";
[@bs.get] external multiEntry: t => bool = "";
[@bs.get] external unique: t => bool = "";

[@bs.send]
external getKey_:
  (t, Js.Nullable.t(Idb_Query.t)) =>
  Js.Promise.t(Js.Json.t) =
  "getKey";

let getKey = (self: t, ~query: option(Idb_Query.t)=?, ()) =>
  getKey_(self, Js.Nullable.fromOption(query))