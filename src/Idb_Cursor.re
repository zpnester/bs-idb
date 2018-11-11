type t;

[@bs.get] external direction: t => Idb_IDBCursorDirection.t = "direction";
[@bs.get] external key_: t => Js.Nullable.t(Idb_Types.any) = "key";
[@bs.get]
external primaryKey_: t => Js.Nullable.t(Idb_Types.any) = "primaryKey";

[@bs.get] external value: t => Idb_Types.any = "value";

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

let key = (self: t) => self->key_->Js.Nullable.toOption;

let primaryKey = (self: t) => self->primaryKey_->Js.Nullable.toOption;

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