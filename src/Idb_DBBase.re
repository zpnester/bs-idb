type t;

[@bs.get] external name: t => string = "name";
[@bs.get] external version: t => int = "version";
[@bs.get]
external objectStoreNames_: t => Js.Array.array_like(string) = "objectStoreNames";

let objectStoreNames = (self: t) =>
  self->objectStoreNames_->Js.Array.from;
  
[@bs.send] external close: t => unit = "close";