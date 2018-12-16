type t;

let complete: t => Js.Promise.t(unit);
let mode: t => string;
let objectStoreNames: t => array(string);
let abort: t => unit;
let objectStore: (t, string) => Idb_ObjectStore.t;