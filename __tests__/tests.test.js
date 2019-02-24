
let host = "http://localhost:4444";

test("test1", () => {
    return page.goto(host + "/test1.html")
        .then(_ => {
            return page.evaluate(() => {
                return result;
            });
        })
        // catch here does not prevent test failing
        .catch(result => {
        	console.log("result", result);
        })
})