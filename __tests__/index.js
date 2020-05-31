import nddcctl from "../lib";

describe("nddcctl", () => {
  let obj;
  beforeAll(() => {
    obj = new nddcctl.MyObject(0);
  });

  it("should export a wrapped object", function () {
    expect(obj.plusOne()).toBe(1);
    expect(obj.plusOne()).toBe(2);
    expect(obj.plusOne()).toBe(3);
  });

  it("should export function that returns nothing", function () {
    expect(nddcctl.nothing()).toBe(undefined);
  });

  it("should export a function that returns a string", function () {
    expect(nddcctl.aString()).toEqual(expect.any(String));
  });

  it("should export a function that returns a boolean", function () {
    expect(nddcctl.aBoolean()).toEqual(expect.any(Boolean));
  });

  it("should export function that returns a number", function () {
    expect(nddcctl.aNumber()).toEqual(expect.any(Number));
  });

  it("should export function that returns an object", function () {
    expect(nddcctl.anObject()).toEqual(expect.any(Object));
  });

  it("should export function that returns an object with a key, value pair", function () {
    expect(nddcctl.anObject()).toEqual({
      key: "value",
    });
  });

  it("should export function that returns an array with some values", function () {
    expect(nddcctl.anArray()).toEqual([1, 2, 3]);
  });

  it("should export function that calls a callback", function () {
    const fn = jest.fn();
    nddcctl.callback(fn);
    expect(fn).toHaveBeenCalledWith();
  });

  it("should export function that calls a callback with a parameter", function () {
    const fn = jest.fn();
    nddcctl.callbackWithParameter(fn);
    expect(fn).toHaveBeenCalledWith("parameter test");
  });

  describe("mainn", () => {
    let result;
    beforeAll(() => {
      result = nddcctl.mainn();
    });

    it("should contain array of screen objects", () => {
      expect(result).toEqual(
        expect.arrayContaining([
          expect.objectContaining({
            id: expect.any(Number),
            displayScale: expect.any(Number),
            rotation: expect.any(Number),
            isBuiltIn: expect.any(Boolean),
            model: expect.any(Number),
            serialNumber: expect.any(Number),
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
            "model": 1,
            "rotation": 0,
            "serialNumber": 0,
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
            "model": 0,
            "rotation": 0,
            "serialNumber": 1093743443,
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
            "model": 0,
            "rotation": 0,
            "serialNumber": 1093882963,
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

  describe("on", () => {
    describe.skip("displaychange", () => {
      const callback = jest.fn();
      beforeAll(() => {
        nddcctl.on("displaychange", callback);
      });

      it("should check if callback have been called", async () => {
        await expect(callback).toHaveBeenCalledWith();
      });
    });

    describe.skip("brightnesschange", () => {
      const callback = jest.fn();
      beforeAll(() => {
        nddcctl.on("brightnesschange", callback);
      });

      it("should call the callback", async () => {
        await expect(callback).toHaveBeenCalledWith("z");
      });
    });
  });
});
