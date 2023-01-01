import 'dart:io';

import 'package:http/http.dart' as http;

class HttpRequests {
  static Future<String?> sendGetRequest(String ip, String url) async {
    String? result;
    await http.get(Uri.parse('http://$ip/$url',), headers: {
      HttpHeaders.contentTypeHeader: 'text/plain'
    }).then((response) {
      if (response.statusCode == 200) {
        result = response.body;
      }
    });
    return result;
  }
}