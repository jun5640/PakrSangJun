(function (root, factory) {

    "use strict";

    if (typeof define === "function" && define.amd) {
        define(["jquery"], factory);
    } else if (typeof exports === "object") {
        if (typeof $ === "undefined") {
            module.exports = factory(require("jquery"));
        } else {
            module.exports = factory($);
        }
    } else {
        root.Mails = factory(root.jQuery);
    }

} (this, function init($, undefined) {

    "use strict";

    var exports = {};

    //
    // Private
    //

    //
    // public 
    //

    exports.Setup = () => {
    }

    return exports;
}));
