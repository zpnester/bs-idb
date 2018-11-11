type t;

[@bs.send]
external get_: (t, Idb_Query.t) => Js.Promise.t(Js.Nullable.t(Idb_Types.any)) =
  "get";

[@bs.send]
external getAll_:
  (t, Js.Nullable.t(Idb_Query.t), Js.Nullable.t(int)) =>
  Js.Promise.t(array(Idb_Types.any)) =
  "getAll";

[@bs.send]
external getAllKeys_:
  (t, Js.Nullable.t(Idb_Query.t), Js.Nullable.t(int)) =>
  Js.Promise.t(array(Idb_Types.any)) =
  "getAllKeys";

[@bs.send]
external count_: (t, Js.Nullable.t(Idb_Query.t)) => Js.Promise.t(int) =
  "count";

[@bs.send]
external openCursor_:
  (t, Js.Nullable.t(Idb_Query.t), Js.Nullable.t(Idb_IDBCursorDirection.t)) =>
  Js.Promise.t(Js.Nullable.t(Idb_Cursor.t)) =
  "openCursor";

[@bs.send]
external openKeyCursor_:
  (t, Js.Nullable.t(Idb_Query.t), Js.Nullable.t(Idb_IDBCursorDirection.t)) =>
  Js.Promise.t(Js.Nullable.t(Idb_Cursor.t)) =
  "openKeyCursor";

let get = (self: t, key: Idb_Query.t) =>
  Js.Promise.(
    self->get_(key) |> then_(maybe => resolve(maybe->Js.Nullable.toOption))
  );

let getAll =
    (self: t, ~query: option(Idb_Query.t)=?, ~count: option(int)=?, ()) =>
  getAll_(
    self,
    Js.Nullable.fromOption(query),
    Js.Nullable.fromOption(count),
  );

let getAllKeys =
    (self: t, ~query: option(Idb_Query.t)=?, ~count: option(int)=?, ()) =>
  self
  ->getAllKeys_(
      Js.Nullable.fromOption(query),
      Js.Nullable.fromOption(count),
    );

let count = (self: t, ~query: option(Idb_Query.t)=?, ()) =>
  self->count_(Js.Nullable.fromOption(query));

/* CURSOR STUFF */

let openCursor =
    (
      self: t,
      ~query: option(Idb_Query.t)=?,
      ~direction: option(Idb_IDBCursorDirection.t)=?,
      (),
    ) =>
  Js.Promise.(
    self
    ->openCursor_(
        Js.Nullable.fromOption(query),
        Js.Nullable.fromOption(direction),
      )
    |> then_(maybe => resolve(Js.Nullable.toOption(maybe)))
  );

let openKeyCursor =
    (
      self: t,
      ~query: option(Idb_Query.t)=?,
      ~direction: option(Idb_IDBCursorDirection.t)=?,
      (),
    ) =>
  Js.Promise.(
    self
    ->openKeyCursor_(
        Js.Nullable.fromOption(query),
        Js.Nullable.fromOption(direction),
      )
    |> then_(maybe => resolve(Js.Nullable.toOption(maybe)))
  );

[@bs.send]
external iterateCursor_: (t, Js.Nullable.t(Idb_IDBCursor.t) => unit) => unit =
  "iterateCursor";

let iterateCursor = (self: t, callback: option(Idb_IDBCursor.t) => unit) => {
  let optionCallback = nullableCursor =>
    callback(Js.Nullable.toOption(nullableCursor));
  self->iterateCursor_(optionCallback);
};

[@bs.send]
external iterateKeyCursor_:
  (t, Js.Nullable.t(Idb_IDBCursor.t) => unit) => unit =
  "iterateKeyCursor";

let iterateKeyCursor = (self: t, callback: option(Idb_IDBCursor.t) => unit) => {
  let optionCallback = nullableCursor =>
    callback(Js.Nullable.toOption(nullableCursor));
  self->iterateKeyCursor_(optionCallback);
};