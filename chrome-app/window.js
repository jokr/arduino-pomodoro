var onConnect = function(connectionInfo) {
  console.log("Connected to board.");
  chrome.runtime.onMessageExternal.addListener(function(request, sender, sendResponse) {
    chrome.serial.send(connectionInfo.connectionId, new ArrayBuffer(1), function() {
      console.log("Sent data to board.");
    });
  });
};

chrome.serial.connect("COM7", {
  bitrate: 9600
}, onConnect);
