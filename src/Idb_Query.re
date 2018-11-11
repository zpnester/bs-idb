type t;

external key: 'a => t = "%identity";

[@bs.val] [@bs.scope "IDBKeyRange"]
external upperBound: ('a, bool) => t = "upperBound";

[@bs.val] [@bs.scope "IDBKeyRange"]
external lowerBound: ('a, bool) => t = "lowerBound";

[@bs.val] [@bs.scope "IDBKeyRange"]
external bound: ('a, 'a, bool, bool) => t = "bound";

[@bs.val] [@bs.scope "IDBKeyRange"] external only: 'a => t = "only";