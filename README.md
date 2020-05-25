# Node DDC Ctl (WIP)

Exposing [kfix/ddcctl][kfix/ddcctl] bindings in node

## Usage

```js
import nddc from 'node-ddcctl'
```

### list connected displays

```typescript
    type Size = {
        width: number,
        height: number,
    }

    type Display = {
        id: number,
        displayScale: number,
        rotation: number,
        isBuiltIn: boolean,
        size: {
            physical: Size,
            pixel: Size
        }
    }

    const displays: Display[] = nddc.mainn()
```


----

### Upcoming

#### Display connect/disconnect event
```js
    nddc.on('displaychange', e => {

    })
```

#### Display brightness change event 

```js
    nddc.on('brightnesschange', e => {

    })
```

#### Display brightness setter

[kfix/ddcctl]: https://github.com/kfix/ddcctl