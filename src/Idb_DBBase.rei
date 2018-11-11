type t;

let name: t => string;
let version: t => Idb_Types.db_version;
let objectStoreNamesArray: t => array(string);
let close: (t, unit) => unit;