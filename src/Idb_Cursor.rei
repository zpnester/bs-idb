type t;

let direction: t => [`next | `nextunique | `prev | `prevunique ];

[@bs.get] external value: t => Js.Json.t = "value";

[@bs.send] external update: (t, 'value) => Js.Promise.t(unit) = "update";

[@bs.send] external delete: t => Js.Promise.t(unit) = "delete";

[@bs.get] external key: t => Js.Json.t = "key";
[@bs.get]
external primaryKey: t => Js.Json.t = "primaryKey";
let advance: (t, int) => Js.Promise.t(option(t));
let continue: (t, ~key: 'key=?, unit) => Js.Promise.t(option(t));
let continuePrimaryKey: (t, 'key, 'pkey) => Js.Promise.t(option(t));