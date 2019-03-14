type t;

[@bs.get] external name: t => string = "name";

[@bs.get] external version: t => int = "version";

let objectStoreNames: t => array(string);

[@bs.send] external close: t => unit = "close";