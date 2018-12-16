type t;

[@bs.get] external complete: t => Js.Promise.t(unit) = "";

[@bs.get] external mode: t => string = "";

[@bs.get]
external objectStoreNames_: t => Idb_DOMStringList.t = "objectStoreNames";
let objectStoreNames = (self: t) =>
  self->objectStoreNames_->Idb_DOMStringList.toArray;

[@bs.send] external abort: t => unit = ""; /* chrome returns number */

[@bs.send] external objectStore: (t, string) => Idb_ObjectStore.t = "";
