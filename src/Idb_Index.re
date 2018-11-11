include Idb_IndexStoreShared;

[@bs.get] external name: t => string = "";
[@bs.get] external keyPath: t => Idb_Types.any = "";
[@bs.get] external multiEntry: t => bool = "";
[@bs.get] external unique: t => bool = "";

[@bs.send]
external getKey_:
  (t, Js.Nullable.t(Idb_Query.t)) =>
  Js.Promise.t(Js.Nullable.t(Idb_Types.any)) =
  "getKey";

let getKey = (self: t, ~query: option(Idb_Query.t)=?, ()) =>
  getKey_(self, Js.Nullable.fromOption(query))
  |> Js.Promise.then_(nullable =>
       Js.Promise.resolve(nullable->Js.Nullable.toOption)
     );