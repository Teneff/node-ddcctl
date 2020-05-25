var nodeDDCCTL = require("../");

describe("nodeDDCCTL", () => {
  let obj;
  beforeAll(() => {
    obj = new nodeDDCCTL.MyObject(0);
  });

  it("should export a wrapped object", function () {
    expect(obj.plusOne()).toBe(1);
    expect(obj.plusOne()).toBe(2);
    expect(obj.plusOne()).toBe(3);
  });

  it("should export function that returns nothing", function () {
    expect(nodeDDCCTL.nothing()).toBe(undefined);
  });

  it("should export a function that returns a string", function () {
    expect(nodeDDCCTL.aString()).toEqual(expect.any(String));
  });

  it("should export a function that returns a boolean", function () {
    expect(nodeDDCCTL.aBoolean()).toEqual(expect.any(Boolean));
  });

  it("should export function that returns a number", function () {
    expect(nodeDDCCTL.aNumber()).toEqual(expect.any(Number));
  });

  it("should export function that returns an object", function () {
    expect(nodeDDCCTL.anObject()).toEqual(expect.any(Object));
  });

  it("should export function that returns an object with a key, value pair", function () {
    expect(nodeDDCCTL.anObject()).toEqual({
      key: "value",
    });
  });

  it("should export function that returns an array with some values", function () {
    expect(nodeDDCCTL.anArray()).toEqual([1, 2, 3]);
  });

  it("should export function that calls a callback", function () {
    const fn = jest.fn();
    nodeDDCCTL.callback(fn);
    expect(fn).toHaveBeenCalled();
  });

  it("should export function that calls a callback with a parameter", function () {
    const fn = jest.fn();
    nodeDDCCTL.callbackWithParameter(fn);
    expect(fn).toHaveBeenCalled();
  });

  describe("mainn", () => {
    let result;
    beforeAll(() => {
      result = nodeDDCCTL.mainn();
    });

    it("should contain array of screen objects", () => {
      expect(result).toEqual(
        expect.arrayContaining([
          expect.objectContaining({
            id: expect.any(Number),
            displayScale: expect.any(Number),
            rotation: expect.any(Number),
            isBuiltIn: expect.any(Boolean),
            size: expect.objectContaining({
              pixel: expect.objectContaining({
                width: expect.any(Number),
                height: expect.any(Number),
              }),
              physical: expect.objectContaining({
                width: expect.any(Number),
                height: expect.any(Number),
              }),
            }),
          }),
        ])
      );
    });

    it("should match snapshot", () => {
      expect(result).toMatchInlineSnapshot(`
        Array [
          Object {
            "displayScale": 2,
            "id": 69734662,
            "isBuiltIn": true,
            "rotation": 0,
            "size": Object {
              "physical": Object {
                "height": 215.31125504449506,
                "width": 344.49800807119203,
              },
              "pixel": Object {
                "height": 1280,
                "width": 2048,
              },
            },
          },
          Object {
            "displayScale": 1,
            "id": 722471575,
            "isBuiltIn": false,
            "rotation": 0,
            "size": Object {
              "physical": Object {
                "height": 294.96773750551284,
                "width": 524.3870888986895,
              },
              "pixel": Object {
                "height": 1080,
                "width": 1920,
              },
            },
          },
          Object {
            "displayScale": 1,
            "id": 722496920,
            "isBuiltIn": false,
            "rotation": 0,
            "size": Object {
              "physical": Object {
                "height": 294.96773750551284,
                "width": 524.3870888986895,
              },
              "pixel": Object {
                "height": 1080,
                "width": 1920,
              },
            },
          },
        ]
      `);
    });
  });
});
