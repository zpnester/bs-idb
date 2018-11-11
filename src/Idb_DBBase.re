type t;

[@bs.get] external name: t => string = "";
[@bs.get] external version: t => Idb_Types.db_version = "";
[@bs.get]
external objectStoreNames_: t => Idb_DOMStringList.t = "objectStoreNames";
let objectStoreNamesArray = (self: t) =>
  self->objectStoreNames_->Idb_DOMStringList.toArray;
[@bs.send] external close: (t, unit) => unit = "";