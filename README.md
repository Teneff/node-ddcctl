# Node DDC Ctl (WIP)

Exposing [kfix/ddcctl][kfix/ddcctl] bindings in node

## Usage

```js
import nddcctl from "node-ddcctl";
```

### list connected displays

```typescript
type Size = {
  width: number;
  height: number;
};

type Display = {
  id: number;
  displayScale: number;
  rotation: number;
  isBuiltIn: boolean;
  size: {
    physical: Size;
    pixel: Size;
  };
};

const displays: Display[] = nddcctl.mainn();
```

---

### Upcoming

- [x] List currently connected displays
  - [x] add isBuiltIn property
- [ ] [Display connect/disconnect event](#Display-connect/disconnect-event)
- [ ] [Display brightness change event](#Display-brightness-change-event)
- [ ] [brightness getter for `Display`s](#brightness-getter-for-Displays)
- [ ] [Display brightness setter for `ExternalDisplay`s](#Display-brightness-setter-for-ExternalDisplays)

#### Display connect/disconnect event

```js
nddcctl.on("displaychange", (e) => {});
```

#### Display brightness change event

```js
nddcctl.on("brightnesschange", (e) => {});
```

#### brightness getter for `Display`s

```diff
    interface Display {
+        getBrightness: () => Promise<number>
    }
```

#### Display brightness setter for `ExternalDisplay`s

```diff
    interface ExternalDisplay {
+        setBrightness: (brightness: number) => Promise<boolean>
    }
```

[kfix/ddcctl]: https://github.com/kfix/ddcctl
