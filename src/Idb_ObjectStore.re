include Idb_IndexStoreShared;

/* Currently Firefox-only (43+) */
type index_locale;

type key_path;
external kpString: string => key_path = "%identity";
external kpStrings: array(string) => key_path = "%identity";
let kpUndefined: key_path = [%raw "undefined"];

module IDBIndexParameters = {
  [@bs.deriving abstract]
  type t = {
    unique: Js.Nullable.t(bool),
    multiEntry: Js.Nullable.t(bool),
    locale: Js.Nullable.t(index_locale),
  };
};

[@bs.get] external name: t => string = "name";
[@bs.get] external keyPath: t => Idb_Types.any = "keyPath";
[@bs.get] external indexNames_: t => Idb_DOMStringList.t = "indexNames";
let indexNamesArray = (self: t) =>
  self->indexNames_->Idb_DOMStringList.toArray;
[@bs.get] external autoIncrement: t => bool = "autoIncrement";

[@bs.send]
external putValueKey_: (t, 'value, Js.Nullable.t('key)) => Js.Promise.t(unit) =
  "put";

let put = (store: t, ~value: 'value, ~key: option('key)=?, ()) =>
  putValueKey_(store, value, Js.Nullable.fromOption(key));

[@bs.send]
external addValueKey_: (t, 'value, Js.Nullable.t('key)) => Js.Promise.t(unit) =
  "add";

let add = (store: t, ~value: 'value, ~key: option('key)=?, ()) =>
  addValueKey_(store, value, Js.Nullable.fromOption(key));

[@bs.send] external delete: (t, 'key) => Js.Promise.t(unit) = "delete";

[@bs.send] external clear: (t, unit) => Js.Promise.t(unit) = "clear";

[@bs.send] external deleteIndex: (t, string) => unit = "deleteIndex";

[@bs.send]
external createIndex_:
  (t, string, key_path, IDBIndexParameters.t) => Idb_Index.t =
  "createIndex";

let createIndex =
    (
      self: t,
      name: string,
      ~keyPath: option([ | `String(string) | `Strings(array(string))])=?,
      ~unique: option(bool)=?,
      ~multiEntry: option(bool)=?,
      (),
    ) => {
  let opts =
    IDBIndexParameters.t(
      ~unique=unique->Js.Nullable.fromOption,
      ~multiEntry=multiEntry->Js.Nullable.fromOption,
      ~locale=Js.Nullable.undefined,
    );
  let keyPath =
    switch (keyPath) {
    | Some(`String(str)) => kpString(str)
    | Some(`Strings(strs)) => kpStrings(strs)
    | None => kpUndefined
    };
  self->createIndex_(name, keyPath, opts);
};

[@bs.send] external index: (t, string) => Idb_Index.t = "index";