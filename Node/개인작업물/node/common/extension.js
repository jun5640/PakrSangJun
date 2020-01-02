//
// Basic Object Extension
//
if (!String.prototype.format) {
    String.prototype.format = function () {
        var args = arguments;
        return this.replace(/{(\d+)}/g, function (match, number) {
            return typeof args[number] != 'undefined' ? args[number] : match;
        });
    };
}

if (!String.prototype.isEmpty) {
    String.prototype.isEmpty = function () {
        return (this.length === 0 || !this.trim());
    };
}

if (!Array.prototype.swap) {
    Array.prototype.swap = function (x, y) {
        var b = this[x];
        this[x] = this[y];
        this[y] = b;
        return this;
    }
}

if (!Array.prototype.resize) {
    Array.prototype.resize = function (newSize, defaultValue) {
        while (newSize > this.length)
            this.push(defaultValue);
        this.length = newSize;
    }
}

if (!Array.prototype.shuffle) {
    Array.prototype.shuffle = function () {
        let copy = this.slice(),
            random = [],
            element, pos;
        while (copy.length > 0) {
            pos = (Math.random() * copy.length) | 0; // bit operation forces 32-bit int
            subarray = copy.splice(pos, 1);
            random.push(subarray[0]);
        }
        return random;
    }
}

var extension = {};

//
// Private
//

//
// Public
//
extension.IsEmpty = function (str) {
    return (!str || 0 === str.length);
}

extension.IsBlank = function (str) {
    return (!str || /^\s*$/.test(str));
}

extension.RandomRange = function (min, max) {
    return Math.floor((Math.random() * (max - min + 1)) + min);
}

extension.toInteger = function (number) {
    return Math.round(      // round to nearest integer
        Number(number)      // type cast your input
    );
};

exports = module.exports = extension;
