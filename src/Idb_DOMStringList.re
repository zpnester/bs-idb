type t;

let toArray: t => array(string) = [%bs.raw
  {|
    function(x) {
        return Array.from(x);
    }
|}
];