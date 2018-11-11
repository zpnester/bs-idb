export function setResult(x) {
    window.result = x;
}

export function expectToBe(a, b) {
    let expect = require("expect");
    expect(a).toBe(b);
}

export function expectToEqual(a, b) {
    let expect = require("expect");
    expect(a).toEqual(b);
}