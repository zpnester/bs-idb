type t;

let direction: t => [`next | `nextunique | `prev | `prevunique ];
let value: t => Js.Json.t;
let update: (t, 'value) => Js.Promise.t(unit);
let delete: t => Js.Promise.t(unit);

let key: t => Js.Json.t;
let primaryKey: t => Js.Json.t;
let advance: (t, int) => Js.Promise.t(option(t));
let continue: (t, ~key: 'key=?, unit) => Js.Promise.t(option(t));
let continuePrimaryKey: (t, 'key, 'pkey) => Js.Promise.t(option(t));