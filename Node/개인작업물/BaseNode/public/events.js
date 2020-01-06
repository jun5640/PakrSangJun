//
// 이밴트 관리
//

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
        root.Events = factory(root.jQuery);
    }

}(this, function init($, undefined) {

    "use strict";

    var templates = {
        create:
            '<form>' + 
                '<div class="form-group"><label>제 목</label><input type="text" class="form-control" id="event-create-name"/></div>' +
                '<div class="form-group"><label>이미지</label><input type="text" class="form-control" id="event-create-url"/></div>' + 
                '<div class="form-group"><label>시작 날짜</label>' + 
                    '<div class="input-group date" id="event-create-start">' +
                        '<input type="text" class="form-control" >' +
                        '<span class="input-group-addon"> <span class="glyphicon glyphicon-calendar"></span></span>' +
                    '</div>' +
                '</div>' + 
                '<div class="form-group"><label>종료 날짜</label>' + 
                    '<div class="input-group date" id="event-create-end">' +
                        '<input type="text" class="form-control"/>' +
                        '<span class="input-group-addon"> <span class="glyphicon glyphicon-calendar"></span></span>' +
                    '</div>' +
                '</div>' + 
            '</form>',
    };

    var exports = {};
    
    //
    // Private
    //
    
    
    //
    // public 
    //
    
    exports.create = function () {
        bootbox.confirm({
            title: '이밴트 생성',
            message: templates.create,
            buttons: {
                cancel: {
                    label: '<i class="fa fa-times"></i> 취소'
                },
                confirm: {
                    label: '<i class="fa fa-check"></i> 확인'
                }
            },
            callback: function (result) {
                if (result) {
                    var name = $("#event-create-name").val();
                    var url = $("#event-create-url").val();
                    if (isEmpty(name) || isEmpty(url)) {
                        bootbox.alert("문제를 입력해 주세요.");
                    } else {
                        var event = {
                            klass : "ActionEventCreate",
                            name : name,
                            url : url,
                            startData : $("#event-create-start").datetimepicker().getDate().toJSON(),
                            endData : $("#event-create-end").datetimepicker().getDate()().toJSON()
                        };
                        
                        ServerRequest(event, function (actionResult) {
                            if (actionResult.result == 1) {
                                bootbox.alert("문제를 생성 하였습니다.");
                            } else {
                                bootbox.alert("문제 등록에 실패하였습니다.<br>오류 코드 {0}".format(actionResult.result));
                            }
                        });
                    }
                }
            }
        });
        var now = new Date();
        $("#event-create-start").datetimepicker({ date: now, autoclose: true, todayBtn: true });
        $("#event-create-end").datetimepicker({ date: now, autoclose: true, todayBtn: true });
    };

    return exports;
}));
