<!DOCTYPE html>
<html>
<head>
 <meta charset='ascii'>
 <title> Question Submitter </title>
 <script src="js/ckeditor/ckeditor.js"></script>
 <style>
   body { font-family: Arial; font-size: 16px; }
   h2 { text-align: left; margin-left: 1in; }
   td:first-child { text-align: right; }
   input[type='text'] { width: 960px; border: 1px solid lightgray;
    border-radius: 3px;}
   textarea { width: 960px; height: 2in; border: 1px solid lightgray;
    border-radius: 3px;}
 </style>
</head>
<body onload='replace();'>
 <div class='body'>
<h2> Question-o-matic v1.1 </h2>
 <form method='post' action='q.php'>
 <table>
  <tr><td>Your Name: <td><input type='text' name='name' value='<?php echo $cdata[1]; ?>' max=63>
  <tr><td>           <td><div id="topSpace"></div> 
  <tr><td>Question:  <td><textarea cols="100" id="q" name="q" rows="10"></textarea>
  <tr><td>Answer:    <td><textarea cols="100" id="a" name="a" rows="10"></textarea>
  <tr><td>           <td><div id="bottomSpace"></div>
  <tr><td colspan=2><input type='submit' onclick="setTimeout(myFunction, 1000);" id="sub" name='add' value='Submit'/>
 </table>
  <script>
  function myFunction() {
    alert('Submitted! Now try logging in as the Boss to see your submit information!');
  }
  var toolbar = [
    { name: 'document', items: [ 'Source', '-', 'NewPage', 'Preview', '-', 'Templates' ] },
    [ 'Cut', 'Copy', 'Paste', 'PasteText', 'PasteFromWord', '-', 'Undo', 'Redo'],	// Defines toolbar group without name.
    { name: 'editing', groups: [ 'find', 'selection', 'spellchecker' ], items: [ 'Scayt' ] },
    ['Table', 'HorizontalRule', 'SpecialChar' ],
    ['Maximize'],
    { name: 'basicstyles', items: [ 'Bold', 'Italic', 'Strike', 'RemoveFormat'] },
    { name: 'paragraph', groups: [ 'list', 'indent', 'blocks', 'align', 'bidi' ], items: [ 'NumberedList', 'BulletedList', '-', 'Outdent', 'Indent', '-', 'Blockquote' ] },
    { name: 'styles', items: [ 'Format' ] }
  ];

  var editprefs = {
    //uiColor: '#14B8C4',
    toolbar: toolbar,
    on: {
      // Check for availability of corresponding plugins.
      pluginsLoaded: function( evt ) {
        var doc = CKEDITOR.document, ed = evt.editor;
        if (!ed.getCommand( 'bold' )) doc.getById( 'exec-bold' ).hide();
        if (!ed.getCommand( 'link' )) doc.getById( 'exec-link' ).hide();
      }
    }
  };

  function replace() {
    CKEDITOR.config.extraPlugins = 'sharedspace';
    CKEDITOR.replace( 'q', editprefs);
    CKEDITOR.replace( 'a', editprefs);
    CKEDITOR.config.sharedSpaces = {
      top: 'topSpace',
      bottom: 'bottomSpace'
    };
  }
 </script>
 </form>
 </div>
</body>
</html>
