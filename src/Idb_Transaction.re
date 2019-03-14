type t;

[@bs.get] external complete: t => Js.Promise.t(unit) = "complete";

[@bs.get] external mode: t => string = "mode";

[@bs.get]
external objectStoreNames_: t => Js.Array.array_like(string) =
  "objectStoreNames";
let objectStoreNames = (self: t) => self->objectStoreNames_->Js.Array.from;

[@bs.send] external abort: t => unit = "abort"; /* chrome returns number */

[@bs.send]
external objectStore: (t, string) => Idb_ObjectStore.t = "objectStore";
