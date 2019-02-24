type t;

[@bs.get] external direction_: t => string = "direction";
let direction = self => switch (direction_(self)) {
  | "next" => `next
  | "nextunique" => `nextunique
  | "prev" => `prev
  | "prevunique" => `prevunique
  | d => failwith("Unknown direction: " ++ d)
};

[@bs.get] external key: t => Js.Json.t = "key";
[@bs.get]
external primaryKey: t => Js.Json.t = "primaryKey";

[@bs.get] external value: t => Js.Json.t = "value";

[@bs.send] external update: (t, 'value) => Js.Promise.t(unit) = "update";

[@bs.send] external delete: t => Js.Promise.t(unit) = "delete";
[@bs.send]
external advance_: (t, int) => Js.Promise.t(Js.Nullable.t(t)) = "advance";
[@bs.send]
external continue_:
  (t, Js.Nullable.t('key)) => Js.Promise.t(Js.Nullable.t(t)) =
  "continue";

[@bs.send]
external continuePrimaryKey_:
  (t, 'key, 'pkey) => Js.Promise.t(Js.Nullable.t(t)) =
  "continuePrimaryKey";



let advance = (self: t, count: int) =>
  Js.Promise.(
    self->advance_(count) |> then_(c => resolve(Js.Nullable.toOption(c)))
  );

let continue = (self: t, ~key: option('key)=?, ()) =>
  Js.Promise.(
    self->continue_(Js.Nullable.fromOption(key))
    |> then_(c => resolve(Js.Nullable.toOption(c)))
  );

let continuePrimaryKey = (cursor: t, key: 'key, primaryKey: 'pkey) =>
  Js.Promise.(
    cursor->continuePrimaryKey_(key, primaryKey)
    |> then_(c => resolve(Js.Nullable.toOption(c)))
  );