import 'package:drone_app/utils/http_requests.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

final droneRepositoryProvider = Provider<DroneApiRepository>(
  (ref) => DroneApiRepository());

abstract class DroneApi {
  Future<int?> toggleStatus(String ip, String status);
}

class DroneApiRepository implements DroneApi {
  @override
  Future<int?> toggleStatus(String ip, String status) async {
    int? result;
    await HttpRequests.sendGetRequest(
      ip, 'safe?status=$status').then((value) {
      result = int.parse(value!);
    });
    return result;
  }
}