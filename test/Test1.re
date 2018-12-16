open Js.Promise;
open Prelude;

Js.log(Idb.indexedDbSupported());

Idb.idb
->Idb.open_(
    "db1",
    1,
    udb => {
      let upgradeTx = udb->Idb.UpgradeDB.transaction;

      expectToEqual(udb->Idb.UpgradeDB.oldVersion, 0);
      expectToEqual(udb->Idb.UpgradeDB.version, 1);
      expectToEqual(udb->Idb.UpgradeDB.name, "db1");
      expectToEqual(udb->Idb.UpgradeDB.objectStoreNames, [||]);

      udb->Idb.UpgradeDB.createObjectStore("store1", ()) |> ignore;
      udb
      ->Idb.UpgradeDB.createObjectStore(
          "store2", 
          ~keyPath=`String("name"),
          (),
        )
      |> ignore;
      udb->Idb.UpgradeDB.createObjectStore("store3", ~autoIncrement=true, ())
      |> ignore;

      udb->Idb.UpgradeDB.createObjectStore("store10", ()) |> ignore;
      expectToEqual(
        upgradeTx->Idb.Transaction.objectStoreNames,
        [|"store1", "store10", "store2", "store3"|],
      );
      udb->Idb.UpgradeDB.deleteObjectStore("store10");
      expectToEqual(
        upgradeTx->Idb.Transaction.objectStoreNames,
        [|"store1", "store2", "store3"|],
      );

      expectToEqual(upgradeTx->Idb.Transaction.mode, "versionchange");

      let store1 = upgradeTx->Idb.Transaction.objectStore("store1");
      expectToEqual(store1->Idb.ObjectStore.name, "store1");

      let store2 = upgradeTx->Idb.Transaction.objectStore("store2");
      store2
      ->Idb.ObjectStore.createIndex(
          "index1",
          ~keyPath=`Strings([|"age"|]),
          (),
        )
      |> ignore;
      /* store2->ObjectStore.deleteIndex("index1"); */

      /* upgradeTx->complete
         |> then_(_ => {
           Js.log("Upgrade completed");
           resolve();
         }); */

      /* upgradeTx->abort; */
      /* udb->close(); */
      ();
    },
  )
|> then_(db => {
     let tx = db->Idb.DB.transaction(`String("store1"), `readonly);
     let store1 = tx->Idb.Transaction.objectStore("store1");
     expectToEqual(store1->Idb.ObjectStore.name, "store1");

     store1->Idb.ObjectStore.getAll()
     |> then_(values => {
          expectToEqual(values, [||]);

          let tx = db->Idb.DB.transaction(`String("store1"), `readwrite);
          let store1 = tx->Idb.Transaction.objectStore("store1");

          store1->Idb.ObjectStore.put(~value="bar", ~key="foo", ());
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store1"), `readonly);
          let store = tx->Idb.Transaction.objectStore("store1");

          store->Idb.ObjectStore.getAll();
        })
     |> then_(values => {
          expectToEqualAny(values, [|"bar"|]);

          let tx = db->Idb.DB.transaction(`String("store3"), `readwrite);
          let store3 = tx->Idb.Transaction.objectStore("store3");
          store3->Idb.ObjectStore.put(~value="first", ());
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store3"), `readwrite);
          let store3 = tx->Idb.Transaction.objectStore("store3");
          store3->Idb.ObjectStore.put(~value="second", ());
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store3"), `readwrite);
          let store3 = tx->Idb.Transaction.objectStore("store3");
          store3->Idb.ObjectStore.put(~value="third", ());
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store3"), `readwrite);
          let store3 = tx->Idb.Transaction.objectStore("store3");

          store3->Idb.ObjectStore.delete(2);
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store3"), `readonly);
          let store3 = tx->Idb.Transaction.objectStore("store3");

          store3->Idb.ObjectStore.getAll();
        })
     |> then_(all => {
          expectToEqualAny(all, [|"first", "third"|]);
          resolve();
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store3"), `readwrite);
          let store3 = tx->Idb.Transaction.objectStore("store3");
          store3->Idb.ObjectStore.clear;
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store3"), `readwrite);
          let store3 = tx->Idb.Transaction.objectStore("store3");

          store3->Idb.ObjectStore.getAll();
        })
     |> then_(all => {
          expectToEqualAny(all, [||]);

          resolve();
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          expectToEqual(store2->Idb.ObjectStore.name, "store2");
          expectToEqualAny(store2->Idb.ObjectStore.keyPath, "name");
          expectToEqual(
            store2->Idb.ObjectStore.indexNamesArray,
            [|"index1"|],
          );
          expectToEqual(store2->Idb.ObjectStore.autoIncrement, false);

          let index1 = store2->Idb.ObjectStore.index("index1");
          expectToEqual(index1->Idb.Index.name, "index1");
          expectToEqualAny(index1->Idb.Index.keyPath, [|"age"|]);
          expectToEqual(index1->Idb.Index.multiEntry, false);
          expectToEqual(index1->Idb.Index.unique, false);

          resolve(
            store2
            ->Idb.ObjectStore.put(~value={"name": "jane", "age": 20}, ()),
          );
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          resolve(
            store2
            ->Idb.ObjectStore.add(~value={"name": "john", "age": 30}, ()),
          );
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          resolve(store2->Idb.ObjectStore.getAll());
        })
     |> then_(all => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          expectToEqualAny(
            all,
            [|{"name": "jane", "age": 20}, {"name": "john", "age": 30}|],
          );

          store2->Idb.ObjectStore.get(Idb.Query.key("john"));
          /* |> then_(_ =>
               tx->Idb.Transaction.complete
             ) */
        })
     |> then_(maybeJohn => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2"); 

          expectToEqualAny(maybeJohn, {"name": "john", "age": 30});
          store2->Idb.ObjectStore.get(Idb.Query.key("unknown"));
        })
     |> then_(maybeUnknown => {
          expectToEqual(Js.typeof(maybeUnknown), "undefined");

          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          store2->Idb.ObjectStore.getAllKeys();
        })
     |> then_(keys => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          expectToEqualAny(keys, [|"jane", "john"|]);
          store2->Idb.ObjectStore.count();
        })
     |> then_(cnt => {
          expectToEqual(cnt, 2);

          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          store2->Idb.ObjectStore.count(~query=Idb.Query.only("jane"), ());
        })
     |> then_(cnt => {
          expectToEqual(cnt, 1);

          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          store2->Idb.ObjectStore.openCursor();
        })
     |> then_(maybeCursor => {
          expectToEqual(maybeCursor->Belt.Option.isSome, true);
          let cursor = maybeCursor->Belt.Option.getExn;

          expectToEqual(cursor->Idb.Cursor.direction, "next");
          expectToEqualAny(cursor->Idb.Cursor.key, "jane");
          expectToEqualAny(cursor->Idb.Cursor.primaryKey, "jane");
          expectToEqualAny(
            cursor->Idb.Cursor.value,
            {"name": "jane", "age": 20},
          );

          /* cursor->Cursor.continue(); */
          cursor->Idb.Cursor.advance(1);
        })
     |> then_(maybeCursor => {
          expectToEqual(maybeCursor->Belt.Option.isSome, true);
          let cursor = maybeCursor->Belt.Option.getExn;
          expectToEqualAny(
            cursor->Idb.Cursor.value,
            {"name": "john", "age": 30},
          );

          cursor->Idb.Cursor.continue();
        })
     |> then_(maybeCursor => {
          expectToEqual(maybeCursor->Belt.Option.isSome, false);

          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          let arr = [||];
          Js.Promise.make((~resolve, ~reject as _) =>
            store2
            ->Idb.ObjectStore.iterateCursor(c =>
                switch (c) {
                | Some(c) =>
                  arr |> Js.Array.push(c->Idb.IDBCursor.value) |> ignore;
                  c->Idb.IDBCursor.continue();
                | None => resolve(. arr)
                }
              )
          );
        })
     |> then_(result => {
          expectToEqualAny(
            result,
            [|{"age": 20, "name": "jane"}, {"age": 30, "name": "john"}|],
          );

          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          let arr = [||];
          Js.Promise.make((~resolve, ~reject as _) =>
            store2
            ->Idb.ObjectStore.iterateKeyCursor(c =>
                switch (c) {
                | Some(c) =>
                  arr |> Js.Array.push(c->Idb.IDBCursor.key) |> ignore;
                  c->Idb.IDBCursor.continue();
                | None => resolve(. arr)
                }
              )
          );
        })
     |> then_(result => {
          expectToEqualAny(result, [|"jane", "john"|]);

          resolve();
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          store2
          ->Idb.ObjectStore.openCursor(
              ~query=Idb.Query.key("john"),
              ~direction=Idb.IDBCursorDirection.prev,
              (),
            );
        })
     |> then_(maybeCursor => {
          let cursor = maybeCursor->Belt.Option.getExn;
          cursor->Idb.Cursor.update({"name": "john", "age": 31});
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          let index1 = store2->Idb.ObjectStore.index("index1");
          index1->Idb.Index.getKey(~query=Idb.Query.key([|31|]), ());
        })
     |> then_(pk => {
          expectToEqualAny(pk, "john");
          resolve();
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          let index1 = store2->Idb.ObjectStore.index("index1");

          index1->Idb.Index.openCursor();
        })
     |> then_(maybeCursor => {
          let cursor = maybeCursor->Belt.Option.getExn;
          cursor->Idb.Cursor.continuePrimaryKey([|25|], "john");
        })
     |> then_(maybeCursor => {
          let cursor = maybeCursor->Belt.Option.getExn;
          expectToEqualAny(
            cursor->Idb.Cursor.value,
            {"name": "john", "age": 31},
          );
          resolve();
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          store2
          ->Idb.ObjectStore.openCursor(~query=Idb.Query.key("jane"), ());
        })
     |> then_(maybeCursor => {
          let cursor = maybeCursor->Belt.Option.getExn;
          cursor->Idb.Cursor.delete;
        })
     |> then_(_ => {
          let tx = db->Idb.DB.transaction(`String("store2"), `readwrite);
          let store2 = tx->Idb.Transaction.objectStore("store2");

          store2->Idb.ObjectStore.getAll();
        })
     |> then_(all => {
          expectToEqualAny(all, [|{"age": 31, "name": "john"}|]);
          Js.log("OK");
          resolve();
        });
   })
|> setResult;