chrome.management.getAll(function(extensions) {
  var arduinoApp = extensions.filter(extension => extension.name === "Arduino Pomodoro App");

  if (arduinoApp.length) {
    arduinoApp = arduinoApp[0];
  }

  chrome.runtime.onMessage.addListener(function(request, sender, sendResponse) {
    chrome.runtime.sendMessage(arduinoApp.id, request);
  });
});
