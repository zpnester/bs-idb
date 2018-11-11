[@bs.val] [@bs.module "./prelude"] external setResult: Js.Promise.t('a) => unit = "";

[@bs.val] [@bs.module "./prelude"] external assert_: 'a => unit = "assert"; 


[@bs.val] [@bs.module "./prelude"] external expectToBe: ('a, 'a) => unit = "";

[@bs.val] [@bs.module "./prelude"] external expectToEqual: ('a, 'a) => unit = "expectToEqual";

[@bs.val] [@bs.module "./prelude"] external expectToEqualAny: ('a, 'b) => unit = "expectToEqual";

