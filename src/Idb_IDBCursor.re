type t;
type idb_cursor_source;

[@bs.get] external source: t => idb_cursor_source = "source";
[@bs.get] external direction: t => Idb_IDBCursorDirection.t = "direction";
[@bs.get] external key_: t => Js.Nullable.t(Idb_Types.any) = "key";
[@bs.get] external value: t => Idb_Types.any = "value";

[@bs.send] external advance: (t, int) => unit = "advance";

[@bs.send] external continue_: (t, Js.Nullable.t('key)) => unit = "continue";

[@bs.send]
external continuePrimaryKey: (t, 'key, 'pkey) => unit = "continuePrimaryKey";

[@bs.send] external delete: t => Idb_IDBRequest.t = "delete";
[@bs.send] external update: (t, 'value) => Idb_IDBRequest.t = "update";

let key = (self: t) => self->key_->Js.Nullable.toOption;

let continue = (cursor: t, ~key: option('key)=?, ()) =>
  cursor->continue_(Js.Nullable.fromOption(key));