
var arrayScreen = ["help", "state", "event", "question", "room", "option"];
var OnChangeScreen = function (name) {
    var count = arrayScreen.length;
    for (var i = 0; i < count; i++) {
        var screen = document.getElementById(arrayScreen[i]);
        if (arrayScreen[i] == name) {
            if (screen != null) screen.style.display = "";
        } else {
            if (screen != null) screen.style.display = "none";
        }
    }
};

//
// 옵션 관리
//
var optionFrom = '<a class="option-data list-group-item list-group-item-action" href="#" option-id="{0}"> {1} </a>'
var RequstServerOptions = function () {
    $('#option-list').empty();
    $('#option-detail').hide();
    $('#options-wait').show();
    var requestOption = {
        klass : "ActionOptions",
    };
    
    ServerRequest(requestOption, function (resultAction) {
        if (resultAction.result == 1) {
            var options = resultAction.options;
            var count = options.length;
            for (var i = 0; i < count; i++) {
                var option = options[i];
                $('#option-list').append(optionFrom.format(option.id, option.name));
            }
            
            $('.option-data').click(function () {
                var active = $('.option-data.active');
                if (active) { active.removeClass('active'); }
                
                var $this = $(this);
                if (!$this.hasClass('active')) {
                    $this.addClass('active');
                }
                
                RequstOption($this.attr('option-id'));
            });
        } else {
            bootbox.alert("서버 관리 정보 요청에 실패하였습니다.<br>오류 코드 {0}".format(resultAction.result));
        }
        $('#options-wait').hide();
    });
}

var selectOption = null;
var RequstOption = function (id) {
    $('#option-detail').hide();
    $('#option-wait').show();
    
    var requestOption = {
        klass : "ActionOption",
        id : id
    };
    
    ServerRequest(requestOption, function (resultAction) {
        if (resultAction.result == 1) {
            selectOption = resultAction.option;
            $('#menu-option-name').text(selectOption.name);
            $('#option-detail').show();
            OptionPageSelecter(selectOption);
        } else {
            bootbox.alert("옵션 상세정보 요청에 실패하였습니다.<br>오류 코드 {0}".format(resultAction.result));
        }
        $('#option-wait').hide();
    });
}

var optionPages = ["option-Final"];
var optionPagesFunction = [
    function () {
        var openValue = selectOption.value.open ? selectOption.value.open : 0;
        $('#option-editor-final-open').val(openValue);
        $('#option-editor-final-open option[value=0]').attr("selected", openValue == 0);
        $('#option-editor-final-open option[value=1]').attr("selected", openValue == 1);
    }
];

var OptionPageSelecter = function (option) {
    var name = 'option-{0}'.format(option.key);
    var count = optionPages.length;
    for (var i = 0; i < count; i++) {
        var screen = document.getElementById(optionPages[i]);
        if (optionPages[i] == name) {
            if (screen != null) screen.style.display = "";
            optionPagesFunction[i]();
        } else {
            if (screen != null) screen.style.display = "none";
        }
    }
}

var optionCrateFrom = '<form class="form-horizontal">' +
    '<div class="form-group"><label for="option-create-name" class="col-sm-3 control-label">이름</label>' +
    '<div class="col-sm-9"><input type="text" class="form-control" id="option-create-name" placeholder="점검"></input></div></div>' +
    '<div class="form-group"><label for="option-create-type" class="col-sm-3 control-label">형</label>' +
    '<div class="col-sm-9"><select class="form-control" id="option-create-type"><option value = "0">BOOL</option><option value = "1">NUMBER</option><option value = "2">문자</option></select></div></div>' +
    '<div class="form-group optoin-type-select" value="0"><label for="option-create-bool-value" class="col-sm-3 control-label">값</label>' +
    '<div class="col-sm-9"><select class="form-control" id="option-create-bool-value"><option value = "true">On</option><option value = "false">Off</option></select></div></div>' +
    '<div class="form-group optoin-type-select" value="1"><label for="option-create-number-value" class="col-sm-3 control-label">값</label>' +
    '<div class="col-sm-9"><input type="number" class="form-control" id="option-create-number-value" placeholder="1234"></input></div></div>' +
    '<div class="form-group optoin-type-select" value="2"><label for="option-create-text-value" class="col-sm-3 control-label">값</label>' +
    '<div class="col-sm-9"><input type="text" class="form-control" id="option-create-text-value" placeholder="값"></input></div></div>' +
    '</form>';
var addOptionData = function () {
    bootbox.confirm({
        title: '변수 만들기',
        message: optionCrateFrom,
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
                
                var name = $('#option-create-name').val();
                if (isEmpty(name)) {
                    bootbox.alert("변수의 이름를 입력해 주세요.");
                } else {
                    
                    var type = Number($('#option-create-type').val());
                    var value;
                    switch (type) {
                        case 0:
                            value = Number($('#option-create-bool-value option:selected').val());
                            break;
                        case 1:
                            value = Number($('#option-create-number-value').val());
                            break;
                        case 2:
                            value = $('#option-create-text-value').val();
                            break;
                    }
                    
                    var optionValue = {
                        name : name,
                        type : type,
                        value : value
                    };
                }
            }
        }
    });
    
    $('div[value="0"].optoin-type-select').show();
    $('#option-create-type').change(function () {
        var selectedValue = Number($("#option-create-type option:selected").val());
        for (var i = 0; i < 3; i++) {
            var select = $('div[value="{0}"].optoin-type-select'.format(i));
            if (i == selectedValue) select.show();
            else select.hide();
        }
    });
}

var RequstSaveOption = function (option) {
    $('#option-wait').show();
    
    var requstSaveMissionRoom = {
        klass : "ActionSaveOption",
        option : option,
    };
    
    ServerRequest(requstSaveMissionRoom, function (resultAction) {
        if (resultAction.result != 1) {
            bootbox.alert("옵션 저장 중 오류가 발생하였습니다.<br>오류 코드 {0}".format(resultAction.result));
        }
        $('#option-wait').hide();
    });
}

$(document).ready(function () {
    //
    // 탑메뉴 이밴트 처리
    //
    $('.top-menu').click(function () {
        var active = $('.top-menu.active');
        if (active) { active.removeClass('active'); }
        
        var $this = $(this);
        if (!$this.hasClass('active')) {
            $this.addClass('active');
        }
        
        // 옵션에 따른 처리
        var func = $this.attr('func');
        switch (func) {
            case 'state':
                OnChangeScreen(func);
                break;
            case 'event':
                OnChangeScreen(func);
                break;
            case 'mail':
                OnChangeScreen(func);
                break;
            case 'option':
                OnChangeScreen(func);
                break;
        }
    });

    //
    // 이밴트 제어 메뉴
    //
    $('.event-menu').click(function () {
        var $this = $(this);
        var func = $this.attr('func');
        switch (func) {
            case 'event-create':
                Events.create();
                break;
        }
    });
    
    //
    // 옵션 제어 메뉴
    //
    $('#requst-options').click(RequstServerOptions);
    $('.menu-option').click(function () {
        var $this = $(this);
        var func = $this.attr('func');
        switch (func) {
            case 'option-save':
                RequstSaveOption(selectOption);
                break;
        }
    });
    
    $('.option-editor-final').change(function () {
        selectOption.value = {
            open : Number($('#option-editor-final-open option:selected').val())
        };
    });
});
