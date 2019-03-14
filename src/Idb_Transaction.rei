type t;

[@bs.get] external complete: t => Js.Promise.t(unit) = "complete";

[@bs.get] external mode: t => string = "mode";

let objectStoreNames: t => array(string);

[@bs.send] external abort: t => unit = "abort";

[@bs.send]
external objectStore: (t, string) => Idb_ObjectStore.t = "objectStore";
