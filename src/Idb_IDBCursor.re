type t;
type idb_cursor_source;

[@bs.get] external source: t => idb_cursor_source = "source";
[@bs.get] external direction_: t => string = "direction";
let direction = self =>
  switch (direction_(self)) {
  | "next" => `next
  | "nextunique" => `nextunique
  | "prev" => `prev
  | "prevunique" => `prevunique
  | d => failwith("Unknown direction: " ++ d)
  };

[@bs.get] external key: t => Js.Json.t = "key";
[@bs.get] external value: t => Js.Json.t = "value";

[@bs.send] external advance: (t, int) => unit = "advance";

[@bs.send] external continue_: (t, Js.Nullable.t('key)) => unit = "continue";

[@bs.send]
external continuePrimaryKey: (t, 'key, 'pkey) => unit = "continuePrimaryKey";

[@bs.send] external delete: t => Idb_IDBRequest.t = "delete";
[@bs.send] external update: (t, 'value) => Idb_IDBRequest.t = "update";

let continue = (cursor: t, ~key: option('key)=?, ()) =>
  cursor->continue_(Js.Nullable.fromOption(key));
