type t;

let key: 'a => t;

let upperBound: ('a, bool) => t;

let lowerBound: ('a, bool) => t;

let bound: ('a, 'a, bool, bool) => t;

let only: 'a => t;
