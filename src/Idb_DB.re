include Idb_DBBase;

[@bs.send]
external transaction:
  (
    t,
    [@bs.unwrap] [ | `String(string) | `Strings(array(string))],
    [@bs.string] [ | `readonly | `readwrite]
  ) =>
  Idb_Transaction.t =
  "transaction";
