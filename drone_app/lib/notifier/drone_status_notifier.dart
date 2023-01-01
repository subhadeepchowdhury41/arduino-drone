import 'package:audioplayers/audioplayers.dart';
import 'package:drone_app/repository/drone_api_repository.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

final statusNotifierProvider = StateNotifierProvider<DroneStatusNotifier, int?>((ref) {
  return DroneStatusNotifier(ref);
});

class DroneStatusNotifier extends StateNotifier<int?> {
  final Ref ref;
  DroneStatusNotifier(this.ref) : super(null);
  String? _ip;
  bool ipConfirmed = false;
  bool loading = false;
  get ip => _ip;
  void setIp(String ip) {
    ipConfirmed = false;
    _ip = ip;
  }
  void setStatus(int status) {
    state = status;
  }
  Future<void> toggleStatus(int status) async {
    loading = true;
    print('$status, $ip');
    await ref.read(droneRepositoryProvider).toggleStatus(ip, status.toString())
    .then((current) {
      setStatus(current!);
      AudioPlayer().play(AssetSource(current == 1 ? 'audio/aaaugh.mp3'
      : 'audio/short-augh.mp3'));
      ipConfirmed = true;
    }).catchError((err, stack) {
      throw Exception('Error sending request');
    });
    loading = false;
  }
}